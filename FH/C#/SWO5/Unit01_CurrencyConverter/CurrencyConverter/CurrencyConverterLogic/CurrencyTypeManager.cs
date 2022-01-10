using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SWO5.Currency.DAL;
using SWO5.Currency.DAL.SQLe;

namespace SWO5.Currency.Logic
{
    class CurrencyTypeManager : IManager<CurrencyType>
    {
        private ICurrencyTypeDao currencyTypeDao = DaoFactorySQLe.CurrencyTypeDao;

        public CurrencyType Create(CurrencyType entity)
        {
            entity.Id = currencyTypeDao.Create(entity);
            return entity;
        }

        public IList<CurrencyType> FindAll()
        {
            return currencyTypeDao.ReadAll();
        }

        public CurrencyType FindById(long identity)
        {
            return currencyTypeDao.ReadForIdentity(identity);
        }

        public CurrencyType Update(CurrencyType entity)
        {
            entity.Id = currencyTypeDao.Update(entity);
            return entity;
        }
    }
}
