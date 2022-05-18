{
  description = "arameia - a small story game in c";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils = {
      inputs.nixpkgs.follows = "nixpkgs";
      url = "github:numtide/flake-utils";
    };
  };

  outputs = { self, nixpkgs, flake-utils, ... }@inputs:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
        rec {
          defaultApp = packages.arameia; # apps.arameia
          defaultPackage = packages.arameia;
          devShell = packages.arameia.overrideAttrs (prev: {
            buildInputs = with pkgs; prev.buildInputs ++ [
              gnumake
              valgrind
            ];
          });

          apps.arameia = {
            type = "app";
            program = "${defaultPackage}/bin/arameia";
          };
          packages.arameia = pkgs.stdenv.mkDerivation {
            name = "arameia";
            pname = "arameia";
            version = "1.0";
            src = ./src;

            buildInputs = with pkgs; [
              SDL2
              SDL2_image
              libpng
            ];
            makeFlags = [
              "DESTDIR=$(out)"
            ];
          };
        }
      );
}
