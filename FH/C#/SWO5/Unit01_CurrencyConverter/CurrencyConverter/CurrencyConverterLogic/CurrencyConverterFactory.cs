
using SWO5.Currency.Domain;

namespace SWO5.Currency.Logic
{
    public class CurrencyConverterFactory
    {

        public static ICurrencyConverter CreateCurrencyConverter()
        {
            // Version 1: very basic implementation of BL
            // return new SimpleCurrencyConverter();
            // Version 2: xml-based currency converter
            // return new XmlBasedCurrencyConverter();
            // Version 3: ado.net based currency converter
            return new SQLeBasedCurrencyConverter();
        }

        public static IManager<CurrencyType> CreateCurrencyTypeManager()
        {
            return new CurrencyTypeManager();
        }

        public static IManager<ExchangeRate> CreateExchangeRateManager()
        {
            return new ExchangeRateManager();
        }

        public static IManager<Instant> CreateInstantManager()
        {
            return new InstantManager();
        }

        public static IManager<Country> CreateCountryManager()
        {
            return new CountryManager();
        }


    }
}
