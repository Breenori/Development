using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL.SQLe
{
    static class DomainExtensions
    {
        public static CurrencyType ToCurrencyType( this IDataRecord record )
        {
            return new CurrencyType
            {
                Id = (long)record["id"],
                Code = (string)record["code"],
                Name = (string)record["name"]
            };

        }

        public static Country ToCountry( this IDataRecord record )
        {
            return new Country { Id = (long)record["id"], Code=(string)record["code"], Name = (string)record["name"] };
        }

        public static ExchangeRate ToExchangeRate( this IDataRecord record )
        {
            return new ExchangeRate { Id = (long)record["id"], Rate = (double)record["rate"] };
        }


        public static Instant ToInstant( this IDataRecord record )
        {
            return new Instant { Id = (long)record["id"], Time = (DateTime)record["time"] };
        }

    }
}
