using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.Text;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices.Marshalling;
using System.Text;
using System.Threading;

namespace GaiaiLogic.SourceGenerators
{

    [Generator]
    public sealed class SciterModelGenerator : IIncrementalGenerator
    {
        public void Initialize(IncrementalGeneratorInitializationContext context)
        {
            var modelClasses = context.SyntaxProvider
            .CreateSyntaxProvider(
                predicate: IsClassWithISciterModel,
                transform: TransformToModelClass)
            .Where(static m => m is not null);

            context.RegisterSourceOutput(modelClasses, (context, modelClass) =>
            {
                var source = GeneratePartialClass(modelClass);
                var originalName = modelClass?.Identifier.Text ?? "";
                context.AddSource($"{originalName}_Generated.cs", SourceText.From(source, Encoding.UTF8));
            });
        }

        private static bool IsClassWithISciterModel(SyntaxNode syntaxNode, CancellationToken cancellationToken)
        {
            var classDeclaration = syntaxNode as ClassDeclarationSyntax;
            if (classDeclaration is null) return false;

            var modelInterface = classDeclaration?.Identifier.Text.EndsWith("PseudoSomModel") ?? false;

            return modelInterface;
        }

        private static ClassDeclarationSyntax? TransformToModelClass(GeneratorSyntaxContext context, CancellationToken cancellationToken)
        {
            var classDeclaration = (ClassDeclarationSyntax)context.Node;
            return classDeclaration; // You might want to do more here if needed
        }

        private static string GeneratePartialClass(ClassDeclarationSyntax? modelClass)
        {
            //Debugger.Launch();
            var className = modelClass?.Identifier.Text ?? "";
            var namespaceName = modelClass?.FirstAncestorOrSelf<NamespaceDeclarationSyntax>()?.Name.ToString() ?? "Global";

            var properties = modelClass?.Members
                .Where(a => a is PropertyDeclarationSyntax)
                .Cast<PropertyDeclarationSyntax>()
                .Where(
                    a => a.Identifier.Text != "Unique" &&
                    a.Modifiers.Any(SyntaxKind.PublicKeyword)
                )
                .Select(
                    a => new
                    {
                        a.Identifier.Text,
                        HasGet = a.AccessorList?.Accessors.Any(SyntaxKind.GetAccessorDeclaration) ?? false,
                        HasSet = a.AccessorList?.Accessors.Any(SyntaxKind.SetAccessorDeclaration) ?? false,
                        Type = a.Type.ToString()
                    }
                )
                .ToList();

            var propertyList = string.Join(", ", properties?.Select(a => $"\"{a.Text}\"") ?? []);
            var getProperties = properties?
                .Where(a => a.HasGet)
                .Select(
                    a =>
                    {
                        return a.Type switch
                        {
                            "int" => $"case \"{a.Text}\": return Host.CreateValue({a.Text});",
                            "long" => $"case \"{a.Text}\": return Host.CreateValue({a.Text});",
                            "double" => $"case \"{a.Text}\": return Host.CreateValue({a.Text});",
                            "float" => $"case \"{a.Text}\": return Host.CreateValue({a.Text});",
                            "string" => $"case \"{a.Text}\": return Host.CreateValue({a.Text});",
                            _ => ""
                        };
                    }
                )
                .ToList();
            var getPropertiesFull = string.Join("\n", getProperties ?? []);
            var setProperties = properties?
                .Where(a => a.HasGet)
                .Select(
                    a =>
                    {
                        return a.Type switch
                        {
                            "int" => $"case \"{a.Text}\": {{ {a.Text} = Host.GetValueInt32(ref value); return true; }}",
                            "long" => $"case \"{a.Text}\": {{ {a.Text} = Host.GetValueInt64(ref value); return true; }}",
                            "double" => $"case \"{a.Text}\": {{ {a.Text} = Host.GetValueDouble(ref value); return true; }}",
                            "float" => $"case \"{a.Text}\": {{ {a.Text} = Host.GetValueDouble(ref value); return true; }}",
                            "string" => $"case \"{a.Text}\": {{ {a.Text} = Host.GetValueString(ref value); return true; }}",
                            _ => ""
                        };
                    }
                )
                .ToList();
            var setPropertiesFull = string.Join("\n", setProperties ?? []);
            var methods = modelClass?.Members
                .Where(a => a is MethodDeclarationSyntax)
                .Cast<MethodDeclarationSyntax>()
                .Where(
                    a =>
                        a.Identifier.Text != "GetPropetyValue" &&
                        a.Identifier.Text != "SetPropetyValue" &&
                        a.Identifier.Text != "CallMethod" &&
                        a.Identifier.Text != "GetProperties" &&
                        a.Identifier.Text != "GetMethods" &&
                        a.Modifiers.Any(SyntaxKind.PublicKeyword) &&
                        a.ReturnType.ToString() == "SciterValue" &&
                        a.ParameterList.Parameters.Any(a => a.Identifier.Text == "parameters" && a.Type?.ToString() is "IEnumerable<SciterValue>" or "List<SciterValue>" or "HashSet<SciterValue>")
                )
                .Select(
                    a => new
                    {
                        a.Identifier.Text
                    }
                )
                .ToList();
            var methodsList = string.Join(", ", methods?.Select(a => $"\"{a.Text}\"") ?? []);

            var template = $@"
using System;
using EmptyFlow.SciterAPI;
using EmptyFlow.SciterAPI.Client.PseudoSom;

namespace {namespaceName}
{{
    internal partial class {className} : IPseudoSomModel
    {{

            private string m_unique = """";

            private SciterAPIHost Host {{ get; set; }}

            public string Unique => m_unique;

            public SciterValue GetPropetyValue(string name) {{
                switch (name) {{
                    {getPropertiesFull}
                }}
                return Host.CreateNullValue();
            }}

            public bool SetPropetyValue(SciterValue value, string name) {{
                switch (name) {{
                    {setPropertiesFull}
                }}

                return false;
            }}

            public SciterValue CallMethod(string name, IEnumerable<SciterValue> parameters) {{
                return Host.CreateNullValue();
            }}

            public HashSet<string> GetProperties() {{
                return new HashSet<string>([{propertyList}]);
            }}

            public HashSet<string> GetMethods() {{
                return new HashSet<string>([{methodsList}]);
            }}

            public string GetModelName() {{
                return ""{className}"";
            }}

            public void SetUnique(string unique) {{
                m_unique = unique;
            }}

    }}
}}";
            return template;
        }
    }

}
