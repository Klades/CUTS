using System;
using System.Data;
using System.Collections;
using MySql.Data.MySqlClient;


namespace Actions.DataBaseActions
{
  public class DataBaseActions
  {
    private MySqlConnection conn_;

    public DataBaseActions ( string ConnectionString )
    {
      this.conn_ = new MySqlConnection( ConnectionString );
      try
      { this.conn_.Open(); }
      catch
      {
        throw new SystemException( "Failed to open DataBase connection. " +
          "Do you have MySql installed and turned on?" );
      }
    }

    ~DataBaseActions ()
    {
      if (this.conn_.State != ConnectionState.Closed)
        this.conn_.Close();
    }

    public void ExecuteMySql ( string sql )
    {
      MySqlCommand comm = new MySqlCommand( sql, conn_ );
      comm.ExecuteNonQuery();
    }

    public void ExecuteMySql ( MySqlCommand comm )
    {
      comm.ExecuteNonQuery();
    }

    public int ExecuteMySqlScalar ( string sql )
    {
      MySqlCommand comm = new MySqlCommand( sql, conn_ );
      object obj = comm.ExecuteScalar();
      return (int)obj;
    }

    public int ExecuteMySqlScalar ( MySqlCommand comm )
    {
      object obj = comm.ExecuteScalar();
      return (int)obj;
    }    

    public MySqlCommand GetCommand ( string sql )
    {
      MySqlCommand comm = conn_.CreateCommand();
      comm.CommandText = sql;
      return comm;
    }

    public DataTable ExecuteMySqlAdapter ( string sql )
    {
      MySqlDataAdapter da = new MySqlDataAdapter( sql, conn_);
      DataSet ds = new DataSet();
      da.Fill( ds );
      return ds.Tables[0];
    }
    public DataTable ExecuteMySqlAdapter ( MySqlCommand command )
    {
      MySqlDataAdapter da = new MySqlDataAdapter( command );
      DataSet ds = new DataSet();
      da.Fill( ds );
      return ds.Tables[0];
    }


    public Array ExecuteMySqlReader ( string sql, string ColumnName )
    {
      MySqlCommand comm = new MySqlCommand( sql, this.conn_ );
      MySqlDataReader r = comm.ExecuteReader();
      ArrayList al = new ArrayList();
      while (r.Read())
        al.Add( r.GetString( ColumnName ) );
      return al.ToArray();
    }

    public DataRow ExecuteMySqlRow ( MySqlCommand comm )
    {
      DataTable dt = this.ExecuteMySqlAdapter( comm );
      return dt.Rows[0];
    }

  }

}

