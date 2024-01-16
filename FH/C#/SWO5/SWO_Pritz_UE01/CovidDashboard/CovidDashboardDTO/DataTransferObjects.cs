using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DTO
{
    public class StateDto
    {
        public long Id { get; set; }
        public string Name { get; set; }
    }

    public class DistrictDto
    {
        public long Id { get; set; }
        public StateDto ResponsibleState { get; set; }
        public string Name { get; set; }
        public long Population { get; set; }
    }

    public class UserDto
    {
        public long Id { get; set; }
        public string Name { get; set; }
        public string Password { get; set; }
    }

        public class ReportGetDto
    {
        public long Id { get; set; }
        public DateTime Date { get; set; }
        public DistrictDto ResponsibleDistrict { get; set; }
        public long Infected { get; set; }
        public long Recovered { get; set; }
        public long Deceased { get; set; }
        public double Incidence { get; set; }
        public UserDto FromUser { get; set; }
    }

    public class ReportPostDto
    {
        public DateTime Date { get; set; }
        public DistrictDto ResponsibleDistrict { get; set; }
        public long Infected { get; set; }
        public long Recovered { get; set; }
        public long Deceased { get; set; }
        public double Incidence { get; set; }
        public UserDto FromUser { get; set; }
    }

    


}
