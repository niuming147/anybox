package com.ppdai.jni;

public class XUtil {
	static {
		System.loadLibrary("myjni");
	}

	private static native String getAESKeyFromJNI(String plainText);

	public static String getAESKey(String plainStr){
		return getAESKeyFromJNI(plainStr);
	}
}