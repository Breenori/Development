using Microsoft.Data.SqlClient;
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
            return record.ToCountry();
        }

        protected override IDbCommand ToInsertCommand(Country entity, SqlConnection conn)
        {
            throw new NotImplementedException();
        }

        protected override IDbCommand ToUpdateCommand(Country entity, SqlConnection conn)
        {
            throw new NotImplementedException();
        }
    }
}
