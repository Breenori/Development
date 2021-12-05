using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL.SQLe
{
    [DaoFactoryCandidate(ProviderName = "Microsoft SQL Server")]
    public class DaoFactorySQLe : IDaoFactory
    {
        public IStateDao StateDao => new StateDaoSQLe();

        public IDistrictDao DistrictDao => new DistrictDaoSQLe();

        public IUserDao UserDao => new UserDaoSQLe();

        public IReportDao ReportDao => new ReportDaoSQLe();
    }
}
