let
    // Define the function with a parameter
    FetchWorkItemDescription = (workItemId as number) as text =>
        let
            // Fetch the JSON document using the dynamic URL
            GetDocument = Json.Document(VSTS.Contents(Text.Format("https://dev.azure.com/[Organization]/[Project]/_apis/wit/workitems/#{0}", {workItemId}))),
            // Convert to table
            ConvertToTable = Record.ToTable(GetDocument[fields]),
            // Transpose the table to switch rows and columns
            TransposedTable = Table.Transpose(ConvertToTable),
            // Promote the first row to headers
            PromotedHeaders = Table.PromoteHeaders(TransposedTable, [PromoteAllScalars=true]),
            // Attempt to fetch 'System.Description' and handle possible errors
            DescriptionResult = try PromotedHeaders[System.Description]{0} otherwise "",
            // Check for null or empty string to return 0 if true
            Description = if DescriptionResult = "" then "0" else DescriptionResult
        in
            Description
in
    FetchWorkItemDescription