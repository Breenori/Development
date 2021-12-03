using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL
{
    public interface IInstantDao : IDao<Instant>
    {

        Instant FindCurrentInstant();

    }
}
