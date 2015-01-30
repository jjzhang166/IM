
package com.CrossApp.IM;
import android.app.Activity;

import android.content.Context;

import org.CrossApp.lib.Cocos2dxActivity;
import org.CrossApp.lib.Cocos2dxGLSurfaceView;



import android.os.Bundle;
import android.util.Log;

public class IM extends Cocos2dxActivity{
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
	}
	
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// IM should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("CrossApp_cpp");
    }     
}
