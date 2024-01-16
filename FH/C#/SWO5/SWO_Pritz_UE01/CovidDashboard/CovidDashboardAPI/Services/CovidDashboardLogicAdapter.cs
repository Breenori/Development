using SWO5.Dashboard.Domain;
using SWO5.Dashboard.DTO;
using SWO5.Dashboard.Logic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SWO5.Dashboard.API.Services
{
    public class CovidDashboardLogicAdapter
    {
        private readonly IManager<Report> reportManager = CovidDashboardFactory.CreateReportManager();

        public IManager<Report> ReportManager { get { return reportManager; } }
    }

    public static class ReportExtensions
    {
        public static ReportGetDto ToGetDto(this Report report)
        {
            return new ReportGetDto
            {
                Id = report.Id,
                Date = report.Date,
                ResponsibleDistrict = new DistrictDto {
                    Id = report.ResponsibleDistrict.Id,
                    Name = report.ResponsibleDistrict.Name,
                    Population = report.ResponsibleDistrict.Population,
                    ResponsibleState = new StateDto {
                        Id = report.ResponsibleDistrict.ResponsibleState.Id,
                        Name = report.ResponsibleDistrict.ResponsibleState.Name
                    }
                },
                Infected = report.Infected,
                Recovered = report.Recovered,
                Deceased = report.Deceased,
                Incidence = report.Incidence,
                FromUser = new UserDto
                {
                    Id = report.FromUser.Id,
                    Name = report.FromUser.Name,
                    Password = report.FromUser.Password
                }
            };
        }

        public static Report FromPostDto(this ReportPostDto reportDto)
        {
            return new Report
            {
                Date = reportDto.Date,
                ResponsibleDistrict = new District
                {
                    Id = reportDto.ResponsibleDistrict.Id,
                    Name = reportDto.ResponsibleDistrict.Name,
                    Population = reportDto.ResponsibleDistrict.Population,
                    ResponsibleState = new State
                    {
                        Id = reportDto.ResponsibleDistrict.ResponsibleState.Id,
                        Name = reportDto.ResponsibleDistrict.ResponsibleState.Name
                    }
                },
                Infected = reportDto.Infected,
                Recovered = reportDto.Recovered,
                Deceased = reportDto.Deceased,
                Incidence = reportDto.Incidence,
                FromUser = new User
                {
                    Id = reportDto.FromUser.Id,
                    Name = reportDto.FromUser.Name,
                    Password = reportDto.FromUser.Password
                }
            };
        }

        public static UserDto ToUserDto(this User user)
        {
            return new UserDto
            {
                Id = user.Id,
                Name = user.Name,
                Password = user.Password
            };
        }

    }
}
