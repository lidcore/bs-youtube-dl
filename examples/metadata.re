open BsCallback;

BsCallback.finish(
  YoutubeDl.metadata("https://youtu.be/uRr708wY7Nk")
  >> (
    vid => {
      Js.log(vid);
      BsCallback.return();
    }
  ),
);
