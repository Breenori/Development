using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SWO5.Currency.Domain;

namespace SWO5.Currency.EF
{
    public class CurrencyContext : DbContext
    {
        private const string CONNECTION_STRING = @"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=CurrencyEF;Integrated Security=True;Connect Timeout=30;Encrypt=False;TrustServerCertificate=False;ApplicationIntent=ReadWrite;MultiSubnetFailover=False";

        public CurrencyContext() : base()
        {

        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer(CONNECTION_STRING).LogTo(Console.WriteLine);
        }

        public DbSet<CurrencyType> CurrencyTypes { get; set; }
        public DbSet<ExchangeRate> ExchangeRates { get; set; }
        public DbSet<Instant> Instants { get; set; }    
        public DbSet<Country> Countries { get; set; }
    }
}
