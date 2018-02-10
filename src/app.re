type state = {
  gifs: option(array(GifService.gif)),
  loading: bool,
};

type action =
  | Search(string)
  | Loaded(array(GifService.gif));

let search = ({ ReasonReact.state, send }, ~query) => {
  Js.log("search");
  Js.log(state.gifs);
  GifService.fetchGifs(query, (gifs) => send(Loaded(gifs))) |> ignore;
};

let component = ReasonReact.reducerComponent("App");
let make = (_children) => {
  ...component,
  initialState: () => {
    gifs: None,
    loading: false,
  },
  reducer: (action, state) => switch action {
  | Search(query) =>
    ReasonReact.UpdateWithSideEffects({ gifs: None, loading: true } ,self => search(~query, self))

  | Loaded(gifs) =>
    ReasonReact.Update({ loading: false, gifs: Some(gifs) })
  },
  render: ({state, send}) => {
    <div>
      <Controls.Controls onSubmit=((text) => send(Search(text))) />
      <section>
        (ReasonReact.stringToElement(string_of_bool(state.loading)))
        (
          switch state.gifs {
          | None => ReasonReact.nullElement
          | Some(gifs) =>
              gifs |> Array.map(({ id, src }: GifService.gif) => <img src alt=id/>) |> ReasonReact.arrayToElement
          }
        )
      </section>
    </div>
  }
};
