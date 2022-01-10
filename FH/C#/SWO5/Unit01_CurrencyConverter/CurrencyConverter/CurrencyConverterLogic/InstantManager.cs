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
    class InstantManager : IManager<Instant>
    {
        private IInstantDao instantDao = DaoFactorySQLe.InstantDao;
        public Instant Create(Instant entity)
        {
            entity.Id = instantDao.Create(entity);
            return entity;
        }

        public IList<Instant> FindAll()
        {
            throw new NotImplementedException();
        }

        public Instant FindById(long identity)
        {
            throw new NotImplementedException();
        }

        public Instant Update(Instant entity)
        {
            throw new NotImplementedException();
        }
    }
}
