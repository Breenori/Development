using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.WPF
{
    static class ReportExtensions
    {
        public static String ToCsv(this Report report)
        {
            return $"{report.Date.ToShortDateString()};{report.ResponsibleDistrict.ResponsibleState.Name};{report.ResponsibleDistrict.Name};{report.Infected};{report.Recovered};{report.Deceased};{report.Incidence}";
        }
    }
}
