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
    }
}
