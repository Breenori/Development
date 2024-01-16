using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace SWO5.Currency.Domain 
{
    [Table("CurrencyType")]
    public class CurrencyType
    {
        public long Id { get; set; }
        [Required]
        public string Code { get; set; }
        [Required]
        public string Name { get; set; }

        public IList<Country> Countries { get; set; }
        public IList<ExchangeRate> ExchangeRates {get;set;}

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

    [Table("ExchangeRate")]
    public class ExchangeRate
    {
        public long Id { get; set; }

        [ForeignKey("currency_id")]
        public CurrencyType CurrencyType { get; set; }

        [ForeignKey("instant_id")]
        public Instant Instant { get; set; }
        public double Rate { get; set; }

        public override string ToString()
        {
            return $"{CurrencyType} - {Rate:0.00}";
        }

    }

    [Table("Instant")]
    public class Instant
    {
        public long Id { get; set; }
        public DateTime Time { get; set; }
        public IList<ExchangeRate> ExchangeRates { get; set; }
    }

    [Table("Country")]
    public class Country
    {
        public long Id { get; set; }
        public string Name { get; set; }
        public string Code { get; set; }
        [ForeignKey("currency_id")]
        public CurrencyType CurrencyType { get; set; }
    }

}
