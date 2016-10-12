package com.nm147.nmtest2;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
//    	String finals = "ppdai";
//        System.out.println("plain----finals="+finals);
//
//        finals = EncyptUtil.reverse(finals);
//        System.out.println("reverse----finals="+finals);
//
//        finals=finals+"5d0c3e9328d07da09d02145fe52a96be";
//        System.out.println("salt----finals="+finals);
//
//        finals = EncyptUtil.base64Encode(finals);
//        System.out.println("base64----finals="+finals);
//        
//        finals = EncyptUtil.md5Encypt(finals);
//        System.out.println("md5----finals="+finals);
//
//        finals = finals.substring(0, 16);
//        System.out.println("substring----finals="+finals);
//
//        finals = EncyptUtil.upCase(finals);
//        System.out.println("upcase----finals="+finals);

    	
//    	String aaa = HttpRequestUtil.sendPost("http://api.meichai.in/open/checkupdate", "appid=1001&version=3.7");
//    	System.out.println(aaa);

    	String aaa = HttpRequestUtil.sendPost("http://localhost:8901/app/Home/niuming/query", "name=aaa&sex=sss&addr=ddd");
    	System.out.println(aaa);
    	
    }
}
