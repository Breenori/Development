using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL.SQLe
{
    class CountryDaoSQLe : AbstractDao<Country>, ICountryDao
    {
        protected override Country FromDataRecord(IDataRecord record)
        {
            throw new NotImplementedException();
        }
    }
}
