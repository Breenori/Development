using SWO5.Currency.DAL;
using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace SWO5.Currency.Logic
{
    class XmlBasedCurrencyConverter : ICurrencyConverter
    {
        private IList<Instant> instants;
        private IList<Country> countries;
        const string EURO_CODE = "EUR";
        const string EURO_RATES = "eurofxref-hist-90d.xml";
        const string COUNTRIES = "countries.xml";

        public string[] Currencies => throw new NotImplementedException();

        public IList<CurrencyType> CurrencyTypes => throw new NotImplementedException();

        public XmlBasedCurrencyConverter()
        {
            InitFromXml();
        }

        private void InitFromXml()
        {
            var euroRatesXml = File.ReadAllText(EURO_RATES);
            XElement exchangeRates = XElement.Parse(euroRatesXml);
            XNamespace ns = "http://www.ecb.int/vocabulary/2002-08-01/eurofxref";
            var instantResult = from e in exchangeRates.Element(ns + "Cube").Descendants(ns + "Cube")
                                from g in e.Descendants(ns + "Cube")
                                group g by e.Attribute("time").Value into k
                                select new Instant
                                {
                                    Time = DateTime.Parse(k.Key),
                                    ExchangeRates = (from ex in k.ToList()
                                                     select new ExchangeRate
                                                     {
                                                         CurrencyType = new CurrencyType { Code = ex.Attribute("currency").Value },
                                                         Rate = Double.Parse(ex.Attribute("rate").Value, CultureInfo.InvariantCulture)
                                                     }).ToList()
                                };
            if( !instantResult.Any())
            {
                throw new ArgumentException("Could not load XML exchange rates");
            }
            instants = instantResult.ToList();

            var countriesXml = File.ReadAllText(COUNTRIES);
            XElement countriesXe = XElement.Parse(countriesXml);
            var countryResult = from c in countriesXe.Element("CcyTbl").Descendants("CcyNtry")
                                from i in instants
                                from e in i.ExchangeRates
                                where e.CurrencyType.Code.Equals(c.Element("Ccy").Value)
                                select new Country { Name = c.Element("CtryNm").Value, CurrencyType = e.CurrencyType };

            if(!countryResult.Any())
            {
                throw new ArgumentException("Could not load XML countries");
            }
            countries = countryResult.ToList();
        }

        public double ConvertFromTo(string from, string to, double value)
        {
            if (from == null || to == null)
                throw new ArgumentOutOfRangeException(
                   $"The supplied currency code {value} is not supported.");

            if (!IsKnownCurrency(from)
                                || !IsKnownCurrency(to))
                throw new ArgumentOutOfRangeException(
                    "The supplied currency codes are not supported.");

            double toRate = ConvertToEuro(from, 1.0);
            double fromRate = ConvertToEuro(to, 1.0);
            return (value * toRate) / fromRate;
        }

        public double ConvertToEuro(string currency, double value)
        {
            if( IsKnownCurrency(currency) )
            {
                if (currency == EURO_CODE)
                    return value;

                var rate = from i in instants[0].ExchangeRates
                           where i.CurrencyType.Code == currency
                           select i.Rate;
                return value / rate.First();

            }else
            {
                throw new ArgumentOutOfRangeException($"The supplied currency code {currency} is not supported!");
            }
        }

        public bool IsKnownCurrency(string currency)
        {
            return currency == EURO_CODE 
                || instants[0].ExchangeRates.Where(e => e.CurrencyType.Code == currency).Any();
        }

        public IList<Country> FindCountriesFor(CurrencyType currencyType)
        {
            throw new NotImplementedException();
        }

        public IList<Tuple<DateTime, ExchangeRate>> FindExchangeRatesFor(string currencyCode)
        {
            throw new NotImplementedException();
        }
    }
}
