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
    class CountryManager : IManager<Country>
    {
        private ICountryDao countryDao = DaoFactorySQLe.CountryDao;
        public Country Create(Country entity)
        {
            entity.Id = countryDao.Create(entity);
            return entity;
        }

        public IList<Country> FindAll()
        {
            return countryDao.ReadAll();
        }

        public Country FindById(long identity)
        {
            return countryDao.ReadForIdentity(identity);
        }

        public Country Update(Country entity)
        {
            entity.Id = countryDao.Update(entity);
            return entity;
        }
    }
}
