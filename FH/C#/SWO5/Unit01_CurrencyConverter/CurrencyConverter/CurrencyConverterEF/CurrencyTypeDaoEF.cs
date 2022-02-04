using SWO5.Currency.DAL;
using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.EF
{
    public class CurrencyTypeDaoEF : AbstractDaoEF<CurrencyType>, ICurrencyTypeDao
    {
        public override long Create(CurrencyType entity)
        {
            MarkInsertOrUpdate(entity, entity.Id);
            foreach (var country in entity.Countries) MarkInsertOrUpdate(country, country.Id);

            Context.CurrencyTypes.Add(entity);
            Context.SaveChanges();
            return entity.Id;
        }

        public override bool Delete(long identity)
        {
            CurrencyType type = Context.CurrencyTypes.Find(identity);
            if(type != null)
            {
                Context.CurrencyTypes.Remove(type);
            }
            return Context.SaveChanges() > 0;
        } 

        public override IList<CurrencyType> ReadAll()
        {
            return Context.CurrencyTypes.ToList();
        }

        public override CurrencyType ReadForIdentity(long identity)
        {
            return Context.CurrencyTypes.Find(identity);
        }

        public override long Update(CurrencyType entity)
        {
            CurrencyType persisted = Context.CurrencyTypes.Find(entity.Id);
            if(persisted != null)
            {
                persisted.Name = entity.Name;
                persisted.Code = entity.Code;
                Context.SaveChanges();
                return persisted.Id;
            }
            return -1;
        }
    }
}
