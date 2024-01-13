using SWO5.Currency.DAL;
using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.EF
{
    class CountryDaoEF : AbstractDaoEF<Country>, ICountryDao
    {
        public override long Create(Country entity)
        {
            MarkInsertOrUpdate(entity, entity.Id);
            if(entity.CurrencyType != null )
                MarkInsertOrUpdate(entity.CurrencyType, entity.CurrencyType.Id);
            Context.Countries.Add(entity);
            Context.SaveChanges();
            return entity.Id;
        }

        public override bool Delete(long identity)
        {
            Country rate = Context.Countries.Find(identity);
            if (rate != null)
            {
                Context.Countries.Remove(rate);
            }
            return Context.SaveChanges() > 0;
        }

        public override IList<Country> ReadAll()
        {
            return Context.Countries.ToList();
        }

        public IList<Country> ReadForCurrencyType(CurrencyType currency)
        {
            return (from c in Context.Countries
                    where c.CurrencyType.Id == currency.Id
                    select c).ToList();
        }

        public override Country ReadForIdentity(long identity)
        {
            return Context.Countries.Find(identity);
        }

        public override long Update(Country entity)
        {
            Country persisted = Context.Countries.Find(entity.Id);
            if (persisted != null)
            {
                persisted.CurrencyType = entity.CurrencyType;
                Context.SaveChanges();
                return persisted.Id;
            }
            return -1;
        }
    }
}
