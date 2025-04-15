{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell
{
    nativeBuildInputs = with pkgs; [
        ncurses
    ];

    shellHook = ''
        echo "Welcome!!!"
        echo "This dev shell includes:"
        echo "      ncurses"
        echo "
        ---------- \"Maintained\" by CaylaTheCake ----------
        " | ${pkgs.clolcat}/bin/clolcat
    '';

}
