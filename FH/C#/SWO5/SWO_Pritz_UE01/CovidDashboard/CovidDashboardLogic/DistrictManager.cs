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
    class DistrictManager : IManager<District>
    {
        private IDistrictDao districtDao = DaoFactorySQLe.DistrictDao;

        public District Create(District entity)
        {
            entity.Id = districtDao.Create(entity);
            return entity;
        }

        public bool Delete(District entity)
        {
            return districtDao.Delete(entity);
        }

        public IList<District> FindAll()
        {
            return districtDao.ReadAll();
        }

        public District FindById(long identity)
        {
            return districtDao.ReadForIdentity(identity);
        }

        public District Update(District entity)
        {
            entity.Id = districtDao.Update(entity);
            return entity;
        }
    }
}
