using SWO5.Currency.DAL;
using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.EF
{
    public class InstantDaoEF : AbstractDaoEF<Instant>, IInstantDao
    {
        public override long Create(Instant entity)
        {
            MarkInsertOrUpdate(entity, entity.Id);
            foreach (var exchangeRate in entity.ExchangeRates) MarkInsertOrUpdate(exchangeRate, exchangeRate.Id);
            Context.Instants.Add(entity);
            Context.SaveChanges();
            return entity.Id;
        }

        public override bool Delete(long identity)
        {
            Instant instant = Context.Instants.Find(identity);
            if (instant != null)
            {
                Context.Instants.Remove(instant);
            }
            return Context.SaveChanges() > 0;
        }

        public Instant FindCurrentInstant()
        {
            return (from i in Context.Instants
                    orderby i.Time descending
                    select i).First();
        }

        public override IList<Instant> ReadAll()
        {
            return Context.Instants.ToList();
        }

        public override Instant ReadForIdentity(long identity)
        {
            return Context.Instants.Find(identity);
        }

        public override long Update(Instant entity)
        {
            Instant persisted = Context.Instants.Find(entity.Id);
            if (persisted != null)
            {
                persisted.ExchangeRates = entity.ExchangeRates;
                persisted.Time = entity.Time;
                Context.SaveChanges();
                return persisted.Id;
            }
            return -1;
        }
    }
}
