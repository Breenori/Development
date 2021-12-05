using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL
{
    public interface IReportDao : IDao<Report>
    {
        // Returns all reports dedicated to a given district
        IList<Report> FindReportsForDistrict(string district);
        // Returns all reports dedicated to a given state
        IList<Report> FindReportsForState(string state);

    }
}
