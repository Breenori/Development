using SWO5.Dashboard.DAL;
using SWO5.Dashboard.DAL.SQLe;
using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.Logic
{
    class StateManager : IManager<State>
    {
        private IStateDao stateDao = DaoFactorySQLe.StateDao;

        public State Create(State entity)
        {
            entity.Id = stateDao.Create(entity);
            return entity;
        }

        public bool Delete(State entity)
        {
            return stateDao.Delete(entity);
        }

        public IList<State> FindAll()
        {
            return stateDao.ReadAll();
        }

        public State FindById(long identity)
        {
            return stateDao.ReadForIdentity(identity);
        }

        public State Update(State entity)
        {
            entity.Id = stateDao.Update(entity);
            return entity;
        }
    }
}
