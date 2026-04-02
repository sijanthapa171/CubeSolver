{
  description = "A simple C++ Hello World project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
      pkgs = forAllSystems (system: nixpkgs.legacyPackages.${system});
    in
    {
      packages = forAllSystems (system: {
        default = pkgs.${system}.stdenv.mkDerivation {
          name = "hello-world";
          src = ./.;

          buildPhase = ''
            $CXX -O2 -o hello main.cpp
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp hello $out/bin/
          '';
        };
      });

      devShells = forAllSystems (system: {
        default = pkgs.${system}.mkShell {
          packages = with pkgs.${system}; [
            gcc
          ];
        };
      });
    };
}
