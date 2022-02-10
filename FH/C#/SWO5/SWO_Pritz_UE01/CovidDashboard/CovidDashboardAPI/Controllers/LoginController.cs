using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.IdentityModel.Tokens;
using SWO5.Dashboard.API.Models;
using SWO5.Dashboard.API.Services;
using SWO5.Dashboard.DTO;
using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class LoginController : ControllerBase
    {
        private IConfiguration configuration;

        public LoginController(IConfiguration configuration)
        {
            this.configuration = configuration;
        }
        
        [HttpPost]
        [AllowAnonymous]
        public IActionResult Login([FromBody] UserDto user)
        {
            IActionResult response = Unauthorized();
            user = AuthenticateUser(user);
            if(user == null)
            {
                return response;
            }
            string token = GenerateToken(user);
            return Ok(new { token = token });
        }

        private string GenerateToken(UserDto user)
        {
            var securityKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(configuration["Token:Key"]));
            var credentials = new SigningCredentials(securityKey, SecurityAlgorithms.HmacSha256);
            var claims = new[]
            {
                new Claim(ClaimTypes.NameIdentifier, user.Name)
            };
            var token = new JwtSecurityToken(
                configuration["Token:Issuer"],
                configuration["Token:Issuer"],
                claims,
                expires: DateTime.Now.AddMinutes(120),
                signingCredentials: credentials
            );

            return new JwtSecurityTokenHandler().WriteToken(token);
        }

        private UserDto AuthenticateUser(UserDto user)
        {
            return UserModel.AvailableUsers.Find(u => u.Name.Equals(user.Name) && u.Password.Equals(getHash(user.Password))).ToUserDto();
        }

        private String getHash(String pwd)
        {
            SHA256 sha256 = SHA256.Create();
            byte[] bytes = sha256.ComputeHash(Encoding.UTF8.GetBytes(pwd));
            StringBuilder builder = new StringBuilder();
            for (int i = 0; i < bytes.Length; i++)
            {
                builder.Append(bytes[i].ToString("x2"));
            }
            return builder.ToString();
        }
    }
}
