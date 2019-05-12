Utils.require("codemirror/keymap/vim");
Utils.require("codemirror/lib/codemirror.css");
Utils.require("codemirror/addon/dialog/dialog.css");
Utils.require("codemirror/mode/javascript/javascript");

[@react.component]
let make =
  React.memo((~value, ~onChange=?, ~onSave=?) => {
    let divRef = React.useRef(Js.Nullable.null);

    React.useEffect1(
      () => {
        let options =
          CM.cmprops(
            ~lineNumbers=true,
            ~keyMap="vim",
            ~mode="javascript",
            ~value,
          );

        let cm =
          CM.init(
            Js.Nullable.toOption(React.Ref.(current(divRef))),
            options,
          );

        switch (onSave) {
        | None => ()
        | Some(save) => CM.commands##save #= (e => save(CM.getValue(e)))
        };

        switch (onChange) {
        | None => ()
        | Some(change) =>
          CM.on(
            cm,
            "change",
            e => {
              let value = CM.getValue(e);
              change(value);
            },
          )
        };

        Some(() => ());
      },
      [||],
    );

    <div className=Styles.editor ref={ReactDOMRe.Ref.domRef(divRef)} />;
  });