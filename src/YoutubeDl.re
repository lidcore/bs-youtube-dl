type t;

open BsCallback;

open LidcoreBsNode.Child_process;

type downloader_options = {http_chunk_size: option(int)};

type format = {
  http_headers: option(Js.Dict.t(string)),
  format_note: option(string),
  format: option(string),
  url: option(string),
  vcodec: option(string),
  tbr: option(float),
  abr: option(float),
  fps: option(float),
  player_url: option(string),
  downloader_options: option(downloader_options),
  ext: option(string),
  filesize: option(int),
  format_id: option(string),
  acodec: option(string),
  width: option(int),
  height: option(int),
  resolution: option(string),
};

type thumbnail = {
  id: option(string),
  url: option(string),
};

type video = {
  protocol: option(string),
  extractor: option(string),
  upload_date: option(string),
  creator: option(string),
  series: option(string),
  format_note: option(string),
  chapters: option(string),
  season_number: option(string),
  like_count: option(int),
  duration: option(float),
  fulltitle: option(string),
  player_url: option(string),
  id: option(string),
  view_count: option(string),
  playlist: option(string),
  title: option(string),
  _filename: option(string),
  format: option(string),
  ext: option(string),
  playlist_index: option(int),
  dislike_count: option(int),
  average_rating: option(float),
  abr: option(int),
  uploader_url: option(string),
  subtitles: option(Js.Dict.t(string)),
  age_limit: option(int),
  annotations: option(string),
  webpage_url_basename: option(string),
  acodec: option(string),
  display_id: option(string),
  automatic_captions: option(Js.Dict.t(string)),
  description: option(string),
  tags: option(Js.Array.t(string)),
  requested_subtitles: option(string),
  start_time: option(int),
  uploader: option(string),
  format_id: option(string),
  episode_number: option(int),
  uploader_id: option(string),
  categories: option(Js.Array.t(string)),
  thumbnails: option(Js.Array.t(thumbnail)),
  width: option(int),
  height: option(int),
  fps: option(float),
  formats: option(Js.Array.t(format)),
};

module Decode = {
  let downloader_options = json =>
    Json.Decode.{
      http_chunk_size: json |> optional(field("http_chunk_size", int)),
    };
  let format = json =>
    Json.Decode.{
      http_headers: json |> optional(field("http_headers", dict(string))),
      format_note: json |> optional(field("format_note", string)),
      format: json |> optional(field("format", string)),
      url: json |> optional(field("url", string)),
      vcodec: json |> optional(field("vcodec", string)),
      tbr: json |> optional(field("tbr", Json.Decode.float)),
      abr: json |> optional(field("abr", Json.Decode.float)),
      player_url: json |> optional(field("player_url", string)),
      downloader_options:
        json |> optional(field("downloader_options", downloader_options)),
      ext: json |> optional(field("ext", string)),
      filesize: json |> optional(field("filesize", int)),
      format_id: json |> optional(field("format_id", string)),
      acodec: json |> optional(field("acodec", string)),
      width: json |> optional(field("width", int)),
      height: json |> optional(field("height", int)),
      fps: json |> optional(field("fps", Json.Decode.float)),
      resolution: json |> optional(field("resolution", string)),
    };
  let thumbnail = json =>
    Json.Decode.{
      id: json |> optional(field("id", string)),
      url: json |> optional(field("url", string)),
    };
  let video = json =>
    Json.Decode.{
      protocol: json |> optional(field("protocol", string)),
      extractor: json |> optional(field("extractor", string)),
      upload_date: json |> optional(field("upload_date", string)),
      creator: json |> optional(field("creator", string)),
      width: json |> optional(field("width", int)),
      height: json |> optional(field("height", int)),
      fps: json |> optional(field("fps", Json.Decode.float)),
      series: json |> optional(field("series", string)),
      format_note: json |> optional(field("format_note", string)),
      chapters: json |> optional(field("chapters", string)),
      season_number: json |> optional(field("season_number", string)),
      like_count: json |> optional(field("like_count", int)),
      duration: json |> optional(field("duration", Json.Decode.float)),
      fulltitle: json |> optional(field("fulltitle", string)),
      player_url: json |> optional(field("player_url", string)),
      id: json |> optional(field("id", string)),
      view_count: json |> optional(field("view_count", string)),
      playlist: json |> optional(field("playlist", string)),
      title: json |> optional(field("title", string)),
      _filename: json |> optional(field("_filename", string)),
      format: json |> optional(field("format", string)),
      ext: json |> optional(field("ext", string)),
      playlist_index: json |> optional(field("playlist_index", int)),
      dislike_count: json |> optional(field("dislike_count", int)),
      average_rating:
        json |> optional(field("average_rating", Json.Decode.float)),
      abr: json |> optional(field("abr", int)),
      uploader_url: json |> optional(field("uploader_url", string)),
      subtitles: json |> optional(field("subtitles", dict(string))),
      age_limit: json |> optional(field("age_limit", int)),
      annotations: json |> optional(field("annotations", string)),
      webpage_url_basename:
        json |> optional(field("webpage_url_basename", string)),
      acodec: json |> optional(field("acodec", string)),
      display_id: json |> optional(field("display_id", string)),
      automatic_captions:
        json |> optional(field("automatic_captions", dict(string))),
      description: json |> optional(field("description", string)),
      tags: json |> optional(field("tags", array(string))),
      requested_subtitles:
        json |> optional(field("requested_subtitles", string)),
      start_time: json |> optional(field("start_time", int)),
      uploader: json |> optional(field("uploader", string)),
      format_id: json |> optional(field("format_id", string)),
      episode_number: json |> optional(field("episode_number", int)),
      uploader_id: json |> optional(field("uploader_id", string)),
      categories: json |> optional(field("categories", array(string))),
      thumbnails: json |> optional(field("thumbnails", array(thumbnail))),
      formats: json |> optional(field("formats", array(format))),
    };
};

let metadata = url =>
  execFile(
    "youtube-dl",
    [|"--dump-json", "-f", "best", url|],
    ~maxBuffer=7000.0 *. 1024.0,
  )
  >> (
    ((stdout, _)) => {
      let vid = stdout |> Json.parseOrRaise |> Decode.video;
      return(vid);
    }
  );
