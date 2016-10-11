/**
 * created by niuming, 2016-9-22
 */
 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jni.h>
#include <assert.h>
#include "md5.h"

//指定JAVA类
#define JNIREG_CLASS "com/ppdai/jni/XUtil"

//----biz function start
//用于base64_encode
const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 

//字符串base64_encode
char *base64_encode(const char* data, int data_len) 
{ 
    //int data_len = strlen(data); 
    int prepare = 0; 
    int ret_len; 
    int temp = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    char changed[4]; 
    int i = 0; 
    ret_len = data_len / 3; 
    temp = data_len % 3; 
    if (temp > 0) 
    { 
        ret_len += 1; 
    } 
    ret_len = ret_len*4 + 1; 
    ret = (char *)malloc(ret_len); 
      
    if ( ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < data_len) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(changed, '\0', 4); 
        while (temp < 3) 
        { 
            //printf("tmp = %d\n", tmp); 
            if (tmp >= data_len) 
            { 
                break; 
            } 
            prepare = ((prepare << 8) | (data[tmp] & 0xFF)); 
            tmp++; 
            temp++; 
        } 
        prepare = (prepare<<((3-temp)*8)); 
        //printf("before for : temp = %d, prepare = %d\n", temp, prepare); 
        for (i = 0; i < 4 ;i++ ) 
        { 
            if (temp < i) 
            { 
                changed[i] = 0x40; 
            } 
            else 
            { 
                changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
            } 
            *f = base[changed[i]]; 
            //printf("%.2X", changed[i]); 
            f++; 
        } 
    } 
    *f = '\0'; 
      
    return ret; 
      
} 

//字符串截取函数 
char* substring(char* ch,int pos,int length)  
{  
    char* pch=ch;  
	//定义一个字符指针，指向传递进来的ch地址。  
    char* subch=(char*)calloc(sizeof(char),length+1);  
	//通过calloc来分配一个length长度的字符数组，返回的是字符指针。  
    int i;  
	//只有在C99下for循环中才可以声明变量，这里写在外面，提高兼容性。  
    pch=pch+pos;  
	//是pch指针指向pos位置。  
    for(i=0;i<length;i++)  
    {  
        subch[i]=*(pch++);  
	//循环遍历赋值数组。  
    }  
    subch[length]='\0';//加上字符串结束符。  
    return subch;       //返回分配的字符数组地址。  
}  

//字符串反转函数
char *reverse(char *p)
{
    char *addr=p,temp;
    int i,j=0;
    i=strlen(p)-1;
    while(i>j)
    {
        temp=*(p+i);
        *(p+i--)=*(p+j);
        *(p+j++)=temp;
        }
    return addr;
}

//字符串转大写
char *upcase(char *str)
{
    //string转数组
	int len = strlen(str);
	char strarray[len];
	int i;
	for (i=0;i<len;i++)
	{
		strarray[i]=*(str++);
	}
	
	//转大写
	int j;
	for(j=0;j<strlen(strarray);j++)
	{
		strarray[j] = toupper(strarray[j]);
	}

    char *dest_str;
	//数组再转回string
    dest_str = (char *)malloc(sizeof(char) * (sizeof(strarray) + 1));     
    strncpy(dest_str, strarray, sizeof(strarray));
	
	return dest_str;
}

//字符串转小写
char *lowcase(char *str)
{
    //string转数组
	int len = strlen(str);
	char strarray[len];
	int i;
	for (i=0;i<len;i++)
	{
		strarray[i]=*(str++);
	}
	
	//转小写
	int j;
	for(j=0;j<strlen(strarray);j++)
	{
		strarray[j] = tolower(strarray[j]);
	}

    char *dest_str;
	//数组再转回string
    dest_str = (char *)malloc(sizeof(char) * (sizeof(strarray) + 1));     
    strncpy(dest_str, strarray, sizeof(strarray));
	
	return dest_str;
}

//字符串md5加密
jstring md5(JNIEnv *env, jstring strText)
{
	char* szText = (char*)(*env)->GetStringUTFChars(env, strText, 0);

	MD5_CTX context = { 0 };
	MD5Init(&context);
	MD5Update(&context, szText, strlen(szText));
	unsigned char dest[16] = { 0 };
	MD5Final(dest, &context);
	(*env)->ReleaseStringUTFChars(env, strText, szText);

	int i = 0;
	char szMd5[32] = { 0 };
	for (i = 0; i < 16; i++)
	{
		sprintf(szMd5, "%s%02x", szMd5, dest[i]);
	}

	return (*env)->NewStringUTF(env, szMd5);
}

//核心函数
__attribute__((section (".mytext"))) JNICALL jstring native_getaeskey(JNIEnv *env, jclass clazz, jstring plainText)
{
	char *oldstr,*newstr;
	oldstr = (char*)(*env)->GetStringUTFChars(env, plainText, 0);

	//1 reverse
	newstr=reverse(oldstr);
		
	//2 salt
	strcat(newstr,"5d0c3e9328d07da09d02145fe52a96be");//字符串拼接，结果保存在第一个字符串当中
	
	//3 base64_encode
	int len = strlen(newstr); 
    newstr = base64_encode(newstr, len); 
		
	//4 md5
	jstring jstr = (*env)->NewStringUTF(env, newstr);
	jstr = md5(env,jstr);
	
	//5 substring
	newstr = (char*)(*env)->GetStringUTFChars(env, jstr, 0);
    newstr=substring(newstr,0,16);

	//6 upcase	
	newstr=upcase(newstr);
	
    return (*env)->NewStringUTF(env, newstr);
}
 
//----biz function end

/**
 * Table of methods associated with a single class.
 */
static JNINativeMethod gMethods[] = {
	//把JAVA中的getAESKeyFromJNI方法绑定到C的native_hello，(Ljava/lang/String;)Ljava/lang/String; --()里面代表参数类型，()后面代表返回值类型
    { "getAESKeyFromJNI", "(Ljava/lang/String;)Ljava/lang/String;", (void*)native_getaeskey },
};
 
/**
 * Register several native methods for one class.
 */
static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
 
    return JNI_TRUE;
}
 
 
/**
 * Register native methods for all classes we know about.
 */
static int registerNatives(JNIEnv* env)
{
    if (!registerNativeMethods(env, JNIREG_CLASS, gMethods, 
                                 sizeof(gMethods) / sizeof(gMethods[0])))
        return JNI_FALSE;
 
    return JNI_TRUE;
}
 
/**
 * Set some test stuff up.
 *
 * Returns the JNI version on success, -1 on failure.
 */
jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	printf("----myjni start");

    JNIEnv* env = NULL;
    jint result = -1;
 
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);
 
    if (!registerNatives(env)) {//注册
        return -1;
    }
    /* success -- return valid version number */
    result = JNI_VERSION_1_4;
 
    return result;
}
