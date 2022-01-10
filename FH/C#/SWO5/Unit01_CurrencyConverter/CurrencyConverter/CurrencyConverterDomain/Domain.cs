using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace SWO5.Currency.Domain 
{
    public class CurrencyType
    {
        public long Id { get; set; }
        [Required]
        public string Code { get; set; }
        [Required]
        public string Name { get; set; }

        public override string ToString()
        {
            return $"{Name} - {Code}";
        }

        public override bool Equals(Object other)
        {
            CurrencyType otherC = other as CurrencyType;
            return otherC != null && otherC.Code.Equals(this.Code);
        }

    }

    public class ExchangeRate
    {
        public long Id { get; set; }

        public CurrencyType CurrencyType { get; set; }
        public double Rate { get; set; }

        public override string ToString()
        {
            return $"{CurrencyType} - {Rate:0.00}";
        }

    }

    public class Instant
    {
        public long Id { get; set; }
        public DateTime Time { get; set; }
        public IList<ExchangeRate> ExchangeRates;
    }

    public class Country
    {
        public long Id { get; set; }
        public string Name { get; set; }
        public string Code { get; set; }
        public CurrencyType CurrencyType { get; set; }
    }

}
