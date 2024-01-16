using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.Logic
{
    public static class CovidDashboardFactory
    {
        public static ICovidDashboard CreateCovidDashboard()
        {
            return new SQLeBasedCovidDashboard();
        }

        public static IManager<State> CreateStateManager() 
        {
            return new StateManager();
        }

        public static IManager<District> CreateDistrictManager()
        {
            return new DistrictManager();
        }

        public static IManager<User> CreateUserManager()
        {
            return new UserManager();
        }

        public static IManager<Report> CreateReportManager()
        {
            return new ReportManager();
        }
    }
}
