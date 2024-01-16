using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL
{
    public interface IDaoFactory
    {
        public  static IStateDao StateDao { get; }
        public static IDistrictDao DistrictDao { get; }
        public static IUserDao UserDao {  get; }
        public static IReportDao ReportDao { get; }   
    }
}
