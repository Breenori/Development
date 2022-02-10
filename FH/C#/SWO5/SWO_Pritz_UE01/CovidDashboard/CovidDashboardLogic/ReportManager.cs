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
    class ReportManager : IManager<Report>
    {
        private IReportDao reportDao = DaoFactorySQLe.ReportDao; 
        public Report Create(Report entity)
        {
            entity.Id = reportDao.Create(entity);
            return entity;
        }

        public bool Delete(Report entity)
        {
            return reportDao.Delete(entity);
        }

        public IList<Report> FindAll()
        {
            return reportDao.ReadAll();
        }

        public Report FindById(long identity)
        {
            return reportDao.ReadForIdentity(identity);
        }

        public Report Update(Report entity)
        {
            entity.Id = reportDao.Update(entity);
            return entity;
        }
    }
}
