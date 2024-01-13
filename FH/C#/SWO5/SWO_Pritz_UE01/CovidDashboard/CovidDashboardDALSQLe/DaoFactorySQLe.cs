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
        public static IStateDao StateDao => new StateDaoSQLe();

        public static IDistrictDao DistrictDao => new DistrictDaoSQLe();

        public static IUserDao UserDao => new UserDaoSQLe();

        public static IReportDao ReportDao => new ReportDaoSQLe();
    }
}
