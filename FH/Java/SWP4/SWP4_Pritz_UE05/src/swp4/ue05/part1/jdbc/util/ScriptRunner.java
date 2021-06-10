package swp4.ue05.part1.jdbc.util;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.stream.Stream;

public class ScriptRunner {

    public static void runSqlScript( String scriptFile, String dbConnection ) {
        if( scriptFile == null || !new File( scriptFile ).exists() ) {
            throw new IllegalArgumentException( "Argument scriptFile cannot be null and should point to a valid sql script file." );
        }
        try(final Connection connection = DriverManager.getConnection( dbConnection );) {
            Stream.of(
                    Files.readString(Paths.get(scriptFile)).split(";")).forEach(
                    sql -> {
                        if( sql.trim().length() > 0 ) {
                            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                                statement.execute();
                                System.out.printf("Executing SQL statement -> %s%s%s%n",ConsoleColors.GREEN, sql.trim(), ConsoleColors.RESET );
                            } catch (SQLException e) {
                                System.err.println("Error executing statement -> " + sql);
                                e.printStackTrace();
                            }
                        }
                    });
        } catch(SQLException e) {
            System.err.println( "Error establishing database connection - is the database up an running?" );
            e.printStackTrace();
        } catch( IOException e ) {
            System.err.println( "Error reading database script: " +ConsoleColors.BLUE + scriptFile + ConsoleColors.RESET );
            e.printStackTrace();
        }
    }

}
