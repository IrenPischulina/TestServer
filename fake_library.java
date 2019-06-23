import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class Library
{
    private static String IP = "127.0.0.1";
    private static int port = 9002;

    public static void setNetworksSettings(String newIP, int newPort)
    {
        IP = newIP;
        port = newPort;
    }

    public static void sendElement(String comm)
    {
        DatagramSocket sock = null;
        try
        {
            sock = new DatagramSocket();
            String command = "!" + comm;
            byte[] b = command.getBytes("UTF-8");
            //Отправляем сообщение
            DatagramPacket  dp = new DatagramPacket(b , b.length , InetAddress.getByName(IP) , port);
            sock.send(dp);

        }catch(IOException e)
        {
            System.err.println("IOException " + e);
        }
    }

    public static void sendCurrentState(String comm)
        {
            DatagramSocket sock = null;
            try
            {
                sock = new DatagramSocket();
                String command = "#" + comm;
                byte[] b = command.getBytes("UTF-8");
                //Отправляем сообщение
                DatagramPacket  dp = new DatagramPacket(b , b.length , InetAddress.getByName(IP) , port);
                sock.send(dp);

            }catch(IOException e)
            {
                System.err.println("IOException " + e);
            }
        }

}












/*package pack;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class Biblio
{
    public static void send(String command)
    {
        DatagramSocket sock = null;

        try
        {
            sock = new DatagramSocket();


            byte[] b = command.getBytes("UTF-8");


            //Отправляем сообщение
            DatagramPacket  dp = new DatagramPacket(b , b.length , InetAddress.getByName("10.0.183.148") , 9002);
            sock.send(dp);

        }catch(IOException e)
        {
            System.err.println("IOException " + e);
        }
    }

}


import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
public class Biblio {

    public static void send(String command) {
        try
        {
            Socket s = new Socket("10.0.183.148", 9002);
            DataOutputStream oos = new DataOutputStream(s.getOutputStream());
            while(!s.isOutputShutdown()){
                oos.writeUTF(command);
                oos.flush();
                break;
            }
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}*/
