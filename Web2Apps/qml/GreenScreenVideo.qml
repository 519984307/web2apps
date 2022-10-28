import QtQuick 2.0
import QtMultimedia 5.4

Item {

    Video{
        id:myvideo
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: 720/2
        width: 1280/2

        muted:true
        source:"file:///C:/tmp/videoplayback.mp4"


        Component.onCompleted: {
            play();
        }
    }
    ShaderEffect {
        anchors.fill: myvideo
        visible: true
        smooth: true
        antialiasing: true
        // Any property you add to the ShaderEffectItem is accessible as a
        // "uniform" value in the shader program. See GLSL doc for details.
        // Essentially, this is a value you pass to the fragment shader,
        // which is the same for every pixel, thus its name.

        // Here we add a source item (the scene) as a uniform value. Within the
        // shader, we can access it as a sampler2D which is the type used to
        // access pixels in a texture. So the source item becomes a texture.
        property variant source: ShaderEffectSource {
            // The item you want to apply the effect to
            sourceItem: myvideo
            hideSource: true  // Only show the modified item, not the original
        }

        // This is the fragment shaderc code in GLSL (GL Shading Language)
        fragmentShader: "
            varying highp vec2 qt_TexCoord0;  // The coords within the source item
            uniform sampler2D source;         // The source item texture
            void main(void)
            {
                // Read the source color of the pixel
                vec4 sourceColor = texture2D(source, qt_TexCoord0);

                    if(((sourceColor.r+sourceColor.b)*0.7<sourceColor.g)&&
                        ((sourceColor.r+sourceColor.b+sourceColor.g)>0.4)){
                        float alpha=0;
                        sourceColor *= alpha;
                    }

                gl_FragColor = sourceColor;
            }
        "
    }
}

