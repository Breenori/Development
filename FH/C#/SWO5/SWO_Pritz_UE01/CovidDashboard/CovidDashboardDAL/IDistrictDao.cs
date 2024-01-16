using System.Collections.Generic;
using SWO5.Dashboard.Domain;

namespace SWO5.Dashboard.DAL
{
    public interface IDistrictDao : IDao<District>
    {
        // Returns the districts belonging to the designated state.
        IList<District> ReadForState(string state);
    }
}
