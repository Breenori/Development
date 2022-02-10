using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using SWO5.Dashboard.API.Services;
using SWO5.Dashboard.Domain;
using SWO5.Dashboard.DTO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;

namespace SWO5.Dashboard.API.Controllers
{
    [Route("api/[controller]")]
    [Produces("application/json")]
    [ApiController]
    [Authorize]
    public class ReportController : ControllerBase
    {
        private readonly CovidDashboardLogicAdapter adapter;

        public ReportController(CovidDashboardLogicAdapter adapter)
        {
            this.adapter = adapter;
        }

        [HttpGet]
        public ActionResult<IList<ReportGetDto>> GetReports()
        {
            IList<Report> reports = adapter.ReportManager.FindAll().TakeLast(100).ToList();
            return Ok(reports.Select(c => c.ToGetDto()));
        }

        [HttpGet("{id}")]
        [ProducesResponseType(200)]
        [ProducesResponseType(404)]
        public ActionResult<ReportGetDto> GetReport(long id)
        {
            Report report = adapter.ReportManager.FindById(id);

            return report == null ? NotFound() : Ok(report.ToGetDto());
        }

        [HttpPost]
        [Consumes("application/json")]
        [ProducesResponseType(201)]
        public ActionResult<ReportGetDto> CreateNewReport([FromBody] ReportPostDto postDto)
        {
            Report report = adapter.ReportManager.Create(postDto.FromPostDto());
            return CreatedAtAction(nameof(GetReport), new { id = report.Id }, report.ToGetDto());
        }

    }
}
