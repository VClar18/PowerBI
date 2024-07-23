//Checks 4 columns for the most current date The order of operations is opened, in progress, resolved/closed. 
//therefore the oldest date is opened and most recent date is closed on an ADO ticket 
//this nested IF statement looks first if the resolved is blank, then closed, then in progress, then open and takes the most recent

Current Date = IF(ISBLANK('WorkItems'[ResolvedDate]),
    IF(ISBLANK('WorkItems'[ClosedDate]),
        IF(ISBLANK('WorkItems'[InProgressDate]),
            'WorkItems'[CreatedDate],'WorkItems'[InProgressDate]
        ),
        'WorkItems'[ClosedDate]
    ),
    'WorkItems'[ResolvedDate]
)


//this function calculates the difference between two dates based on hours and then divides the hours by 24 (converting the hours into days)
Duration of Days = ( DATEDIFF ( 'WorkItems'[CreatedDate], IF(ISBLANK('WorkItems'[ClosedDate]),'WorkItems'[Current Date],'WorkItems'[ClosedDate]), HOUR))/24
