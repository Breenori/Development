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
        IList<Report> FindReportsFor(District district);
        IList<Report> FindReportsFor(State state);

    }
}
