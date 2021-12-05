using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL
{
    public interface IDaoFactory
    {
        public IStateDao StateDao { get; }
        public IDistrictDao DistrictDao { get; }
        public IUserDao UserDao {  get; }
        public IReportDao ReportDao { get; }   
    }
}
