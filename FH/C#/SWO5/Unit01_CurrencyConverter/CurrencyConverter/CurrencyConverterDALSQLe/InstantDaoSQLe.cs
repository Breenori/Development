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
            throw new NotImplementedException();
        }
    }
}
