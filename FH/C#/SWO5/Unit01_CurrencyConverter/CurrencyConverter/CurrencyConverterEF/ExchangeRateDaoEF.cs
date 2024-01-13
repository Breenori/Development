using Microsoft.EntityFrameworkCore;
using SWO5.Currency.DAL;
using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.EF
{
    public class ExchangeRateDaoEF : AbstractDaoEF<ExchangeRate>, IExchangeRateDao
    {

        public override long Create(ExchangeRate entity)
        {
            MarkInsertOrUpdate(entity, entity.Id);
            if (entity.CurrencyType != null)
                MarkInsertOrUpdate(entity.CurrencyType, entity.CurrencyType.Id);
            if( entity.Instant != null )
                MarkInsertOrUpdate(entity.Instant, entity.Instant.Id);
            
            Context.ExchangeRates.Add(entity);
            Context.SaveChanges();
            return entity.Id;
        }

        public override bool Delete(long identity)
        {
            ExchangeRate rate = Context.ExchangeRates.Find(identity);
            if (rate != null)
            {
                Context.ExchangeRates.Remove(rate);
            }
            return Context.SaveChanges() > 0;
        }

        public IList<ExchangeRate> FindExchangeRatesFor(Instant instant, string currencyCode)
        {
            return (from i in Context.Instants
                    from e in i.ExchangeRates
                    where i.Id == instant.Id && e.CurrencyType.Code.Equals(currencyCode)
                    select e).ToList();

        }

        public IList<Tuple<DateTime, ExchangeRate>> FindExchangeRatesFor(string currencyCode)
        {
            return (from i in Context.Instants
            from e in i.ExchangeRates
            where e.CurrencyType.Code == currencyCode
            select new Tuple<DateTime, ExchangeRate>( i.Time, e )).ToList();
        }

        public override IList<ExchangeRate> ReadAll()
        {
            return Context.ExchangeRates.ToList();
        }

        public override ExchangeRate ReadForIdentity(long identity)
        {
            return Context.ExchangeRates.Find(identity);
        }

        public override long Update(ExchangeRate entity)
        {
            ExchangeRate persisted = Context.ExchangeRates.Find(entity.Id);
            if (persisted != null)
            {
                persisted.CurrencyType = entity.CurrencyType;
                persisted.Rate = entity.Rate;
                Context.SaveChanges();
                return persisted.Id;
            }
            return -1;
        }
    }
}
