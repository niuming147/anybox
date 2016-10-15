package in.meichai.okhttp;

import java.io.IOException;
import java.lang.ref.WeakReference;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;

import com.squareup.okhttp.Request;
import com.squareup.okhttp.Response;

/**
 * okhttp callback two in one
 * @author niuming,2016-3-18
 */
public class MainOKHttpCallback implements com.squareup.okhttp.Callback {
	private StringParser mParser = new StringParser();
	private static final int CALLBACK_SUCCESSFUL = 1;
	private static final int CALLBACK_FAILED = 2;

	static class UIHandler extends Handler {
		private WeakReference mWeakReference;

		public UIHandler(MainOKHttpCallback callback) {
			super(Looper.getMainLooper());
			mWeakReference = new WeakReference(callback);
		}

		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case CALLBACK_SUCCESSFUL: {
				String t = (String) msg.obj;
				MainOKHttpCallback callback = (MainOKHttpCallback) mWeakReference.get();
				if (callback != null) {
					callback.onResponse(t);
				}
				break;
			}
			case CALLBACK_FAILED: {
				IOException e = (IOException) msg.obj;
				MainOKHttpCallback callback = (MainOKHttpCallback) mWeakReference.get();
				if (callback != null) {
					callback.onFailure(e);
				}
				break;
			}
			default:
				super.handleMessage(msg);
				break;
			}
		}
	}

	private Handler mHandler = new UIHandler(this);

	@Override
	public void onFailure(Request request, IOException e) {
		Message message = Message.obtain();
		message.what = CALLBACK_FAILED;
		message.obj = e;
		mHandler.sendMessage(message);
	}

	@Override
	public void onResponse(Response response) throws IOException {
		if (response.isSuccessful()) {
			String parseResult = mParser.parse(response);
			Message message = Message.obtain();
			message.what = CALLBACK_SUCCESSFUL;
			message.obj = parseResult;
			mHandler.sendMessage(message);
		} else {
			Message message = Message.obtain();
			message.what = CALLBACK_FAILED;
			mHandler.sendMessage(message);
		}
	}

	public void onResponse(String t) {

	}

	public void onFailure(IOException e) {

	}
}
