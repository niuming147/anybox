package in.meichai.okhttp;

import java.io.IOException;

import com.squareup.okhttp.Response;

/**
 * okhttp callback two in one
 * @author niuming,2016-3-18
 */
public class StringParser{
    public String parse(Response response) {
        String result=null;
        try {
            result=response.body().string();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }
}
