using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DaoFactoryCandidate : Attribute
    {
        public string ProviderName { get; set; }
    }
}
