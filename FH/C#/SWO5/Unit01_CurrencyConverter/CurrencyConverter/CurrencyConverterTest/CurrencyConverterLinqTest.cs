using System;
using System.Linq;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using SWO5.Currency.Domain;

namespace SWO5.Currency.Test
{
    [TestClass]
    public class CurrencyConverterLinqTest
    {
        private IList<ExchangeRate> exchangeRates;
        private IList<Instant> instants;


        [TestInitialize]
        public void Initialize()
        {

            exchangeRates = new List<ExchangeRate>() {
                new ExchangeRate(){ CurrencyType = new CurrencyType{ Code = "EUR", Name = "Euro" }, Rate = 1.00 },
                new ExchangeRate(){ CurrencyType = new CurrencyType{ Code = "USD", Name = "US Dollar" }, Rate = 1.17 },
                new ExchangeRate(){ CurrencyType = new CurrencyType{ Code = "GBP", Name = "British Pound" }, Rate = 0.90 },
                new ExchangeRate(){ CurrencyType = new CurrencyType{ Code = "CHF", Name = "Swiss Franks" }, Rate = 1.08 }
            };

            instants = new List<Instant>() {
                new Instant(){ Time = new DateTime( 2020,01,01 ), ExchangeRates = exchangeRates },
                new Instant(){ Time = new DateTime( 2020,02,01 ), ExchangeRates = exchangeRates },
                new Instant(){ Time = new DateTime( 2020,03,01 ), ExchangeRates = exchangeRates },
                new Instant(){ Time = new DateTime( 2020,04,01 ), ExchangeRates = exchangeRates },
                new Instant(){ Time = new DateTime( 2020,05,01 ), ExchangeRates = exchangeRates },
                new Instant(){ Time = new DateTime( 2020,06,01 ), ExchangeRates = exchangeRates },
                new Instant(){ Time = new DateTime( 2020,07,01 ), ExchangeRates = exchangeRates },
                new Instant(){ Time = new DateTime( 2020,08,01 ), ExchangeRates = exchangeRates },
                new Instant(){ Time = new DateTime( 2020,09,01 ), ExchangeRates = exchangeRates }
            };
        }

        [TestMethod]
        public void TestLinq_Where()
        {
            // given -> Initialize

            // when
            var res = from ins in instants
                      where ins.Time < new DateTime(2020, 05, 1)
                      select ins.ToString();

            // then
            Assert.AreEqual(4, res.Count());
        }

        [TestMethod]
        public void TestLinq_OrderBy()
        {
            // given -> Initialize
            // when
            var res = from ex in exchangeRates
                      where ex.Rate > 1.0
                      orderby ex.CurrencyType.Code
                      select ex;

            // then
            Assert.AreEqual(2, res.Count());
            Assert.AreEqual("CHF", res.ToArray()[0].CurrencyType.Code);
            Assert.AreEqual("USD", res.ToArray()[1].CurrencyType.Code);
        }

        [TestMethod]
        public void TestLinq_MultipleFrom()
        {
            // given -> Initialize
            // when
            var res = from ins in instants
                      from ex in ins.ExchangeRates
                      orderby ins.Time descending
                      where ex.CurrencyType.Code == "CHF"
                      select ex;
            // then
            Assert.AreEqual(9, res.Count());
            foreach (var element in res)
            {
                Assert.AreEqual("CHF", element.CurrencyType.Code);
            }
        }

        [TestMethod]
        public void TestLinq_AnonymousClass()
        {
            // given -> Initialize
            // when
            var res = from ins in instants
                      where ins.Time > new DateTime(2020, 05, 01)
                      select new { ins.Time, exchangeRates.Count };
            // then

            Assert.AreEqual(4, res.Count());

        }

    }
}
