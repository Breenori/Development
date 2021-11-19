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
    class InstantDaoSQLe : AbstractDao<Instant>, IInstantDao
    {
        public Instant FindCurrentInstant()
        {
            throw new NotImplementedException();
        }

        protected override Instant FromDataRecord(IDataRecord record)
        {
            return record.ToInstant();
        }

        protected override IDbCommand ToInsertCommand(Instant entity, SqlConnection conn)
        {
            throw new NotImplementedException();
        }

        protected override IDbCommand ToUpdateCommand(Instant entity, SqlConnection conn)
        {
            throw new NotImplementedException();
        }
    }
}
