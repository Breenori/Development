
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using SWO5.Currency.DAL;

namespace SWO5.Currency.EF
{

    public abstract class AbstractDaoEF<T> : IDao<T>
    {
        private CurrencyContext _context;
        protected CurrencyContext Context
        {
            get
            {
                if ( _context == null)
                    _context = new CurrencyContext( );
                return _context;
            }
        }

        protected void MarkInsertOrUpdate(object entity, long id)
        {
            Context.Entry(entity).State = id == 0 ?
                                   EntityState.Added :
                                   EntityState.Modified;
        }

        public abstract long Create(T entity);
        public abstract bool Delete(long identity);
        public abstract IList<T> ReadAll();
        public abstract T ReadForIdentity(long identity);
        public abstract long Update(T entity);
    }
}
