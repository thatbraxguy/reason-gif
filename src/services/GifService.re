type gif = {
    id: string,
    src: string,
};

let giphyHost = "https://api.giphy.com";
let akey = "32fa8eadf5fa4e11ac7e6a3e4a14a881";
let searchBase = giphyHost ++ "/v1/gifs/search?api_key=" ++ akey;

let makeSearchUrl = (~offset=0, ~limit=25, ~query, ()) =>
    searchBase
    ++ "&q=" ++ query
    ++ "&offset=" ++ string_of_int(offset)
    ++ "&limit=" ++ string_of_int(limit);

module Decode {
    open Json;
    let gif = (json) : gif => Decode.{
        id: json |> field("id", string),
        src: json |> at(["images", "original", "url"], string)
    };
    let searchResponse = (json) => Decode.(json |> field("data", array(gif)));
};

let fetchGifs = (query, cb) => {
    Js.log("gif service fetch gifs!");
    Js.Promise.(
        Fetch.fetch(makeSearchUrl(~query, ()))
        |> then_(Fetch.Response.json)
        |> then_(json =>
            json |> Decode.searchResponse
                |> gifs => {
                    cb(gifs);
                    Js.log(gifs);
                    resolve(())
                })
    )
}